FROM ubuntu:latest
WORKDIR /home
COPY . .

# Install dependencies
RUN apt update && apt install -y g++ git cmake make binutils dpkg

# Build and install GoogleTest
RUN git clone https://github.com/google/googletest.git && \
  cd googletest && \
  mkdir build && cd build && \
  cmake .. && \
  make -j$(nproc) && make install && \
  cd /home && rm -rf googletest

# Build program and .deb file
RUN make -j$(nproc) build-deb && \
  dpkg -i counter-v2.0.0.deb || true

CMD ["/bin/count"]

EXPOSE 3000