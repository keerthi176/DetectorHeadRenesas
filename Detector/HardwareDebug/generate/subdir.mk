################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
ASM_SRCS += \
../generate/cstart.asm \
../generate/stkinit.asm 

ASSEMBLER_OBJS += \
generate/cstart.obj \
generate/stkinit.obj 

ASM_DEPS += \
generate/cstart.d \
generate/stkinit.d 

# Each subdirectory must supply rules for building sources it contributes
generate/%.obj: ../generate/%.asm 
	@echo 'Scanning and building file: $<'
	ccrl -subcommand="generate\asmDepSubCommand.tmp" -asmopt=-MF="$(@:%.obj=%.d)" -asmopt=-MT="$(@:%.obj=%.obj)" -asmopt=-MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	ccrl -subcommand="generate\asmSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"


