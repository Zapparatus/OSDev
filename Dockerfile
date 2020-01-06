# Start from ubuntu
FROM ubuntu:latest

# Update package lists and install required tools
RUN apt-get update && \
  apt-get install wget xz-utils make qemu nasm grub-pc-bin xorriso git -y

# Install the cross-compiler
RUN wget http://newos.org/toolchains/x86_64-elf-4.9.1-Linux-x86_64.tar.xz && \
  tar xf x86_64-elf-4.9.1-Linux-x86_64.tar.xz

# Create the working directory and copy the files over
RUN mkdir /osdev
COPY . /osdev
WORKDIR /osdev

# Run qemu
CMD [ "make", "run" ]
