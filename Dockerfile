FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        g++ \
        gdb \
        make \
        valgrind \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /taskforge

COPY . .

RUN make

CMD ["./taskforge"]
