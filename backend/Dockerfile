#build
FROM gcc:11 AS build
WORKDIR /app
RUN apt-get update && \
    apt-get install -y --no-install-recommends libssl-dev
COPY ./httplib.h main.cpp Calculator.cpp Calculator.hpp /app/
#creo eseguibile del calcolatore
RUN g++ -o calculator -std=c++11 main.cpp Calculator.cpp -lssl -lcrypto -lpthread

# Run Time
FROM gcc:11
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    libstdc++6 \
    libssl-dev

WORKDIR /usr/bin/api
#copio eseguibile del calcolatore
COPY --from=build /app/calculator .
EXPOSE 3000
CMD ["./calculator"]