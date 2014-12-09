################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Agent.cpp \
../Agent_factory.cpp \
../Amount_View.cpp \
../Archer.cpp \
../Commander.cpp \
../Component.cpp \
../Composite.cpp \
../Controller.cpp \
../Farm.cpp \
../Geometry.cpp \
../Grid_View.cpp \
../Health_View.cpp \
../Info_View.cpp \
../Local_View.cpp \
../Map_View.cpp \
../Model.cpp \
../Moving_object.cpp \
../Overall_View.cpp \
../Peasant.cpp \
../Sim_object.cpp \
../Soldier.cpp \
../Structure.cpp \
../Structure_factory.cpp \
../Town_Hall.cpp \
../Utility.cpp \
../View.cpp \
../Views.cpp \
../Warrior.cpp \
../p6_main.cpp \
../test.cpp 

OBJS += \
./Agent.o \
./Agent_factory.o \
./Amount_View.o \
./Archer.o \
./Commander.o \
./Component.o \
./Composite.o \
./Controller.o \
./Farm.o \
./Geometry.o \
./Grid_View.o \
./Health_View.o \
./Info_View.o \
./Local_View.o \
./Map_View.o \
./Model.o \
./Moving_object.o \
./Overall_View.o \
./Peasant.o \
./Sim_object.o \
./Soldier.o \
./Structure.o \
./Structure_factory.o \
./Town_Hall.o \
./Utility.o \
./View.o \
./Views.o \
./Warrior.o \
./p6_main.o \
./test.o 

CPP_DEPS += \
./Agent.d \
./Agent_factory.d \
./Amount_View.d \
./Archer.d \
./Commander.d \
./Component.d \
./Composite.d \
./Controller.d \
./Farm.d \
./Geometry.d \
./Grid_View.d \
./Health_View.d \
./Info_View.d \
./Local_View.d \
./Map_View.d \
./Model.d \
./Moving_object.d \
./Overall_View.d \
./Peasant.d \
./Sim_object.d \
./Soldier.d \
./Structure.d \
./Structure_factory.d \
./Town_Hall.d \
./Utility.d \
./View.d \
./Views.d \
./Warrior.d \
./p6_main.d \
./test.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -pedantic -pedantic-errors -Wall -Wextra -Werror -Wconversion -c -fmessage-length=0 -Wno-unused-parameter -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


