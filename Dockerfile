FROM ubuntu:22.04

RUN apt-get -y update
RUN apt-get -y install build-essential
RUN apt-get -y install git
RUN apt-get -y install cmake
RUN apt-get -y install libsfml-dev
RUN apt-get -y install nlohmann-json3-dev
RUN wsl --update
RUN wsl --shutdown
RUN wls --list --verbose

WORKDIR .
COPY ./ ./src
#COPY ./Music ./Music
#COPY ./assets ./assets
#COPY ./include ./include
#COPY ./lib ./lib
#COPY ./CMakeLists.txt ./CMakeLists.txt
#COPY ./main.cpp ./main.cpp
#COPY ./build ./build

RUN cmake -DTESTS_REQUIRED=1 ../src
RUN make

CMD ["./SPACERETARDS"]

