FROM ubuntu:20.04

ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update && apt-get install -y qemu binfmt-support qemu-user

# Create a user.
ARG USERNAME=user
RUN groupadd -g 1000 $USERNAME
RUN useradd -r -u 1000 --create-home -g $USERNAME $USERNAME
USER $USERNAME
WORKDIR /home/$USERNAME

ENV EMULATOR=aarch64
ENV EXECUTABLE="abc"

ENTRYPOINT "qemu-${EMULATOR}" "-L" "/sysroot" "/binaries/${EXECUTABLE}"