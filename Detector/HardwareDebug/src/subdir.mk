################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/PIR.c \
../src/delay.c \
../src/heat.c \
../src/r_cg_adc.c \
../src/r_cg_adc_user.c \
../src/r_cg_cgc.c \
../src/r_cg_cgc_user.c \
../src/r_cg_intc.c \
../src/r_cg_intc_user.c \
../src/r_cg_it.c \
../src/r_cg_it_user.c \
../src/r_cg_port.c \
../src/r_cg_port_user.c \
../src/r_cg_serial.c \
../src/r_cg_serial_user.c \
../src/r_cg_timer.c \
../src/r_cg_timer_user.c \
../src/r_cg_wdt.c \
../src/r_cg_wdt_user.c \
../src/r_main.c \
../src/r_systeminit.c \
../src/smoke.c 

COMPILER_OBJS += \
src/PIR.obj \
src/delay.obj \
src/heat.obj \
src/r_cg_adc.obj \
src/r_cg_adc_user.obj \
src/r_cg_cgc.obj \
src/r_cg_cgc_user.obj \
src/r_cg_intc.obj \
src/r_cg_intc_user.obj \
src/r_cg_it.obj \
src/r_cg_it_user.obj \
src/r_cg_port.obj \
src/r_cg_port_user.obj \
src/r_cg_serial.obj \
src/r_cg_serial_user.obj \
src/r_cg_timer.obj \
src/r_cg_timer_user.obj \
src/r_cg_wdt.obj \
src/r_cg_wdt_user.obj \
src/r_main.obj \
src/r_systeminit.obj \
src/smoke.obj 

C_DEPS += \
src/PIR.d \
src/delay.d \
src/heat.d \
src/r_cg_adc.d \
src/r_cg_adc_user.d \
src/r_cg_cgc.d \
src/r_cg_cgc_user.d \
src/r_cg_intc.d \
src/r_cg_intc_user.d \
src/r_cg_it.d \
src/r_cg_it_user.d \
src/r_cg_port.d \
src/r_cg_port_user.d \
src/r_cg_serial.d \
src/r_cg_serial_user.d \
src/r_cg_timer.d \
src/r_cg_timer_user.d \
src/r_cg_wdt.d \
src/r_cg_wdt_user.d \
src/r_main.d \
src/r_systeminit.d \
src/smoke.d 

# Each subdirectory must supply rules for building sources it contributes
src/%.obj: ../src/%.c 
	@echo 'Scanning and building file: $<'
	ccrl -subcommand="src\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	ccrl -subcommand="src\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"


