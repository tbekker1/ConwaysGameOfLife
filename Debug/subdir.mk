################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Board.cpp \
../Cell.cpp \
../dataGOL.cpp \
../recursiveGOL.cpp \
../sequentialGOL.cpp \
../speculativeGOL.cpp 

OBJS += \
./Board.o \
./Cell.o \
./dataGOL.o \
./recursiveGOL.o \
./sequentialGOL.o \
./speculativeGOL.o 

CPP_DEPS += \
./Board.d \
./Cell.d \
./dataGOL.d \
./recursiveGOL.d \
./sequentialGOL.d \
./speculativeGOL.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


