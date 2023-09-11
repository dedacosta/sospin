# ----------------------------------------------------------------------------
# SOSpin Library
# Copyright (C) 2023 SOSpin Project
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
# You should have received a copy of the GNU General Public License
# along with SOSpin Library.  If not, see <http:#www.gnu.org/licenses/>.
# ----------------------------------------------------------------------------

FROM debian:12.1-slim

LABEL maintainer="David da Costa <david.dacosta@dlr.de>"

RUN apt-get update
RUN apt-get install -y htop cmake

ENTRYPOINT ["tail"] CMD ["-f","/dev/null"]