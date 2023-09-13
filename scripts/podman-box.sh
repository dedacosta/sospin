#!/bin/sh

if [ "$1" = "clean" ]; then
  podman stop --all && podman system prune --all --force && podman rmi --all
  podman pod create sospin-pod
fi

podman image exists sospin:latest
if [ ! "$?" = "0" ]; then
  podman build --tag sospin:latest -f ./Dockerfile
fi

if [ ! "$(podman ps -a -q -f name=demo-sospin)" ]; then
    if [ "$(podman ps -aq -f status=exited -f name=demo-sospin)" ]; then
        # cleanup
        docker rm demo-sospin
    fi
    # run your container
    podman run -d --rm -it --name demo-sospin sospin:latest
fi

if [ "$1" = "start" ]; then
    podman start demo-sospin
    exit 0
fi

if [ "$1" = "stop" ]; then
    podman stop demo-sospin
    exit 0
fi

podman exec -it demo-sospin /bin/bash