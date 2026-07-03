# Base image: GCC 13, includes a modern C++17-capable compiler.
FROM gcc:13

# CMake is not included in the base gcc image, so we install it explicitly.
RUN apt-get update && \
    apt-get install -y cmake && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy the whole project into the image.
COPY . .

# Configure and build using CMake.
RUN mkdir -p build && \
    cd build && \
    cmake .. && \
    make

# Run the compiled executable. Working directory is /app so it finds
# the input/ and output/ folders correctly (mounted as volumes, see
# docker-compose.yml).
CMD ["./build/mlq_scheduler"]
