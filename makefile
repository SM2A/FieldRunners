COMPILER=g++
COMPILE=-c
VERSION= -std=c++11
LIBRARY= -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
RSDL_HEADEAR = Lib/RSDL/src/rsdl.hpp
CC=${COMPILER} ${COMPILE} ${VERSION}

BUILD_DIR=Build
SOURCE_DIR=Src
CLASSES_DIR=Classes
TOWERS_DIR=Towers
ENEMIES_DIR=Enemies
INTERFACES_DIR=Interfaces

all: FieldRunners.out

FieldRunners.out : ${BUILD_DIR}/main.o ${BUILD_DIR}/Tower.o ${BUILD_DIR}/Enemie.o ${BUILD_DIR}/rsdl.o ${BUILD_DIR}/Gatling.o ${BUILD_DIR}/Missile.o ${BUILD_DIR}/Runner.o ${BUILD_DIR}/Scrambler.o ${BUILD_DIR}/Stubborn_Runner.o ${BUILD_DIR}/Super_Trooper.o ${BUILD_DIR}/Tesla.o ${BUILD_DIR}/Back_Ground.o ${BUILD_DIR}/Wave_Handler.o ${BUILD_DIR}/Game.o ${BUILD_DIR}/Tower_Handler.o 
	${COMPILER} ${VERSION} ${BUILD_DIR}/main.o ${BUILD_DIR}/Tower.o ${BUILD_DIR}/Enemie.o ${BUILD_DIR}/Gatling.o ${BUILD_DIR}/Missile.o ${BUILD_DIR}/Tesla.o ${BUILD_DIR}/rsdl.o ${BUILD_DIR}/Runner.o ${BUILD_DIR}/Scrambler.o ${BUILD_DIR}/Stubborn_Runner.o ${BUILD_DIR}/Super_Trooper.o ${BUILD_DIR}/Back_Ground.o ${LIBRARY} ${BUILD_DIR}/Wave_Handler.o ${BUILD_DIR}/Game.o ${BUILD_DIR}/Tower_Handler.o -o FieldRunners.out

${BUILD_DIR}/rsdl.o: ${RSDL_HEADEAR} Lib/RSDL/src/rsdl.cpp
	${CC} Lib/RSDL/src/rsdl.cpp -o ${BUILD_DIR}/rsdl.o

${BUILD_DIR}/main.o: ${SOURCE_DIR}/main.cpp ${SOURCE_DIR}/${INTERFACES_DIR}/Back_Ground.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/Wave_Handler.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/Game.hpp ${RSDL_HEADEAR}
	mkdir -p Build
	${CC} ${SOURCE_DIR}/main.cpp -o ${BUILD_DIR}/main.o

${BUILD_DIR}/Tower.o: ${SOURCE_DIR}/${INTERFACES_DIR}/${TOWERS_DIR}/Tower.hpp ${SOURCE_DIR}/${CLASSES_DIR}/${TOWERS_DIR}/Tower.cpp ${SOURCE_DIR}/${INTERFACES_DIR}/${ENEMIES_DIR}/Enemie.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/Game.hpp
	${CC} ${SOURCE_DIR}/${CLASSES_DIR}/${TOWERS_DIR}/Tower.cpp -o ${BUILD_DIR}/Tower.o

${BUILD_DIR}/Enemie.o: ${SOURCE_DIR}/${INTERFACES_DIR}/${ENEMIES_DIR}/Enemie.hpp ${SOURCE_DIR}/${CLASSES_DIR}/${ENEMIES_DIR}/Enemie.cpp ${SOURCE_DIR}/${INTERFACES_DIR}/Back_Ground.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/Game.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/Wave_Handler.hpp
	${CC} ${SOURCE_DIR}/${CLASSES_DIR}/${ENEMIES_DIR}/Enemie.cpp -o ${BUILD_DIR}/Enemie.o

${BUILD_DIR}/Gatling.o: ${SOURCE_DIR}/${INTERFACES_DIR}/${TOWERS_DIR}/Gatling.hpp ${SOURCE_DIR}/${CLASSES_DIR}/${TOWERS_DIR}/Gatling.cpp ${SOURCE_DIR}/${INTERFACES_DIR}/${TOWERS_DIR}/Tower.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/${ENEMIES_DIR}/Enemie.hpp
	${CC} ${SOURCE_DIR}/${CLASSES_DIR}/${TOWERS_DIR}/Gatling.cpp -o ${BUILD_DIR}/Gatling.o

${BUILD_DIR}/Tesla.o: ${SOURCE_DIR}/${INTERFACES_DIR}/${TOWERS_DIR}/Tesla.hpp ${SOURCE_DIR}/${CLASSES_DIR}/${TOWERS_DIR}/Tesla.cpp ${SOURCE_DIR}/${INTERFACES_DIR}/${TOWERS_DIR}/Tower.hpp
	${CC} ${SOURCE_DIR}/${CLASSES_DIR}/${TOWERS_DIR}/Tesla.cpp -o ${BUILD_DIR}/Tesla.o

${BUILD_DIR}/Missile.o: ${SOURCE_DIR}/${INTERFACES_DIR}/${TOWERS_DIR}/Missile.hpp ${SOURCE_DIR}/${CLASSES_DIR}/${TOWERS_DIR}/Missile.cpp ${SOURCE_DIR}/${INTERFACES_DIR}/${TOWERS_DIR}/Tower.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/${ENEMIES_DIR}/Enemie.hpp
	${CC} ${SOURCE_DIR}/${CLASSES_DIR}/${TOWERS_DIR}/Missile.cpp -o ${BUILD_DIR}/Missile.o

${BUILD_DIR}/Runner.o: ${SOURCE_DIR}/${INTERFACES_DIR}/${ENEMIES_DIR}/Runner.hpp ${SOURCE_DIR}/${CLASSES_DIR}/${ENEMIES_DIR}/Runner.cpp ${SOURCE_DIR}/${INTERFACES_DIR}/${ENEMIES_DIR}/Enemie.hpp
	${CC} ${SOURCE_DIR}/${CLASSES_DIR}/${ENEMIES_DIR}/Runner.cpp -o ${BUILD_DIR}/Runner.o

${BUILD_DIR}/Scrambler.o: ${SOURCE_DIR}/${INTERFACES_DIR}/${ENEMIES_DIR}/Scrambler.hpp ${SOURCE_DIR}/${CLASSES_DIR}/${ENEMIES_DIR}/Scrambler.cpp ${SOURCE_DIR}/${INTERFACES_DIR}/${ENEMIES_DIR}/Enemie.hpp
	${CC} ${SOURCE_DIR}/${CLASSES_DIR}/${ENEMIES_DIR}/Scrambler.cpp -o ${BUILD_DIR}/Scrambler.o

${BUILD_DIR}/Stubborn_Runner.o: ${SOURCE_DIR}/${INTERFACES_DIR}/${ENEMIES_DIR}/Stubborn_Runner.hpp ${SOURCE_DIR}/${CLASSES_DIR}/${ENEMIES_DIR}/Stubborn_Runner.cpp ${SOURCE_DIR}/${INTERFACES_DIR}/${ENEMIES_DIR}/Enemie.hpp
	${CC} ${SOURCE_DIR}/${CLASSES_DIR}/${ENEMIES_DIR}/Stubborn_Runner.cpp -o ${BUILD_DIR}/Stubborn_Runner.o

${BUILD_DIR}/Super_Trooper.o: ${SOURCE_DIR}/${INTERFACES_DIR}/${ENEMIES_DIR}/Super_Trooper.hpp ${SOURCE_DIR}/${CLASSES_DIR}/${ENEMIES_DIR}/Super_Trooper.cpp ${SOURCE_DIR}/${INTERFACES_DIR}/${ENEMIES_DIR}/Enemie.hpp
	${CC} ${SOURCE_DIR}/${CLASSES_DIR}/${ENEMIES_DIR}/Super_Trooper.cpp -o ${BUILD_DIR}/Super_Trooper.o

${BUILD_DIR}/Back_Ground.o: ${SOURCE_DIR}/${INTERFACES_DIR}/Back_Ground.hpp ${SOURCE_DIR}/${CLASSES_DIR}/Back_Ground.cpp ${SOURCE_DIR}/${INTERFACES_DIR}/Tower_Handler.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/Game.hpp
	${CC} ${SOURCE_DIR}/${CLASSES_DIR}/Back_Ground.cpp -o ${BUILD_DIR}/Back_Ground.o

${BUILD_DIR}/Wave_Handler.o: ${SOURCE_DIR}/${INTERFACES_DIR}/Wave_Handler.hpp ${SOURCE_DIR}/${CLASSES_DIR}/Wave_Handler.cpp ${SOURCE_DIR}/${INTERFACES_DIR}/${ENEMIES_DIR}/Enemie.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/${ENEMIES_DIR}/Runner.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/${ENEMIES_DIR}/Scrambler.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/${ENEMIES_DIR}/Stubborn_Runner.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/${ENEMIES_DIR}/Super_Trooper.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/Back_Ground.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/Game.hpp
	${CC} ${SOURCE_DIR}/${CLASSES_DIR}/Wave_Handler.cpp -o ${BUILD_DIR}/Wave_Handler.o

${BUILD_DIR}/Tower_Handler.o: ${SOURCE_DIR}/${INTERFACES_DIR}/Tower_Handler.hpp ${SOURCE_DIR}/${CLASSES_DIR}/Tower_Handler.cpp ${SOURCE_DIR}/${INTERFACES_DIR}/${TOWERS_DIR}/Tower.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/${TOWERS_DIR}/Missile.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/${TOWERS_DIR}/Gatling.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/${TOWERS_DIR}/Tesla.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/Game.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/${ENEMIES_DIR}/Enemie.hpp
	${CC} ${SOURCE_DIR}/${CLASSES_DIR}/Tower_Handler.cpp -o ${BUILD_DIR}/Tower_Handler.o

${BUILD_DIR}/Game.o: ${SOURCE_DIR}/${INTERFACES_DIR}/Game.hpp ${SOURCE_DIR}/${CLASSES_DIR}/Game.cpp
	${CC} ${SOURCE_DIR}/${CLASSES_DIR}/Game.cpp -o ${BUILD_DIR}/Game.o

clean:
	rm FieldRunners.out
	rm ${BUILD_DIR}/*.o
	rmdir Build