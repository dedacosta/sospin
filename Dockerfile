FROM debian:12.1-slim

MAINTAINER	David da Costa <david.dacosta@dlr.de>

RUN apt-get update
RUN apt-get install -y htop

ENTRYPOINT ["tail"] CMD ["-f","/dev/null"]