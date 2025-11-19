FROM gcc:11 AS build
WORKDIR /app
RUN apt-get update && \
    apt-get install -y --no-install-recommends libssl-dev && \
    rm -rf /var/lib/apt/lists/*
COPY ./httplib.h main.cpp Calculator.cpp Calculator.hpp /app/

RUN g++ -o calculator -std=c++11 main.cpp Calculator.cpp -lssl -lcrypto -lpthread
FROM gcc:11
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    libstdc++6 \
    libssl-dev && \
    rm -rf /var/lib/apt/lists/*
WORKDIR /usr/bin/api
COPY --from=build /app/calculator .
EXPOSE 3000
CMD ["./calculator"]