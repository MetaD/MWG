################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Agent.cpp \
../Agent_factory.cpp \
../Archer.cpp \
../Controller.cpp \
../Death_Knight.cpp \
../Farm.cpp \
../Geometry.cpp \
../Model.cpp \
../Moving_object.cpp \
../Peasant.cpp \
../Sim_object.cpp \
../Soldier.cpp \
../Structure.cpp \
../Structure_factory.cpp \
../Town_Hall.cpp \
../Utility.cpp \
../View.cpp \
../Views.cpp \
../Warriors.cpp \
../main.cpp 

OBJS += \
./Agent.o \
./Agent_factory.o \
./Archer.o \
./Controller.o \
./Death_Knight.o \
./Farm.o \
./Geometry.o \
./Model.o \
./Moving_object.o \
./Peasant.o \
./Sim_object.o \
./Soldier.o \
./Structure.o \
./Structure_factory.o \
./Town_Hall.o \
./Utility.o \
./View.o \
./Views.o \
./Warriors.o \
./main.o 

CPP_DEPS += \
./Agent.d \
./Agent_factory.d \
./Archer.d \
./Controller.d \
./Death_Knight.d \
./Farm.d \
./Geometry.d \
./Model.d \
./Moving_object.d \
./Peasant.d \
./Sim_object.d \
./Soldier.d \
./Structure.d \
./Structure_factory.d \
./Town_Hall.d \
./Utility.d \
./View.d \
./Views.d \
./Warriors.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -pedantic -pedantic-errors -Wall -Wextra -Werror -Wconversion -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


