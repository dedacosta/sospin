# ----------------------------------------------------------------------------
# SOSpin Library
# COPYright (C) 2023 SOSpin Project
#
#   Authors:
#
#     Nuno Cardoso (nuno.cardoso@tecnico.ulisboa.pt)
#     David Emmanuel-Costa (david.costa@tecnico.ulisboa.pt)
#     Nuno Gonçalves (nunogon@deec.uc.pt)
#     Catarina Simoes (csimoes@ulg.ac.be)
#
# ----------------------------------------------------------------------------
# This file is part of SOSpin Library.
#
# SOSpin Library is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or any
# later version.
#
# SOSpin Library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a COPY of the GNU General Public License
# along with SOSpin Library.  If not, see <http:#www.gnu.org/licenses/>.
# ----------------------------------------------------------------------------

FROM debian:12.1-slim

LABEL maintainer="David da Costa <david.dacosta@dlr.de>"

RUN apt-get update
RUN apt-get install -y htop g++ python3 doxygen vim cmake

RUN mkdir -p /data/sospin

COPY CMakeLists.txt /data/sospin
COPY package.json /data/sospin
COPY Makefile /data/sospin
COPY src /data/sospin/src
COPY include /data/sospin/include
COPY app /data/sospin/app
COPY test /data/sospin/test
COPY doc /data/sospin/doc

WORKDIR /data/sospin

CMD ["sleep", "infinity"]
