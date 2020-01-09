#!/bin/bash -e

# kubectl run -i --rm --tty --rm debug --image=gcr.io/crimsonmirror/dedicated --restart=Never -- bash

# firewall rules
gcloud compute firewall-rules create game-server-firewall \
  --allow udp:7000-8000,tcp:7000-8000,udp:27015-27030,tcp:27015-27030,icmp \
  --target-tags game-server \
  --description "Firewall to allow game server traffic"

gcloud container clusters create dedicated \
  --cluster-version=1.13 \
  --tags=game-server \
  --scopes=gke-default \
  --num-nodes=1 \
  --no-enable-autoupgrade \
  --machine-type=n1-standard-1

# add custom node pools with labels, delete the default
gcloud container node-pools create game-server-pool \
  --cluster=dedicated \
  --tags=game-server \
  --machine-type=n1-standard-2 --preemptible --disk-type=pd-ssd \
  --num-nodes=1 --min-nodes=1 --max-nodes=2 \
  --node-labels=type=game-server-node

gcloud container node-pools create agones-system-pool \
  --cluster=dedicated \
  --tags=game-server \
  --machine-type=n1-standard-1 --preemptible --disk-type=pd-standard \
  --num-nodes=1 --min-nodes=1 --max-nodes=1 \
  --node-labels=type=agones-system-node

gcloud container node-pools delete default-pool --cluster dedicated

# install agones
kubectl create namespace agones-system
helm repo add agones https://agones.dev/chart/stable
helm install cm-release --namespace agones-system \
  --set gameservers.minPort=7000,gameservers.maxPort=8000 \
  --set agones.ping.replicas=1,agones.allocator.replicas=1,agones.controller.numWorkers=4 \
  --set agones.controller.nodeSelector.type=agones-system-node \
  --set agones.ping.nodeSelector.type=agones-system-node \
  agones/agones

# create gameserver
kubectl create -f Docker/gameserver.yaml

# spin down
# gcloud container clusters resize dedicated --node-pool game-server-pool --num-nodes=0
# gcloud container clusters resize dedicated --node-pool agones-system-pool --num-nodes=0
# spin up
# gcloud container clusters resize dedicated --node-pool game-server-pool --num-nodes=1
# gcloud container clusters resize dedicated --node-pool agones-system-pool --num-nodes=1
