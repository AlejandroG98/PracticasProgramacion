##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=UOCProgrammeEC
ConfigurationName      :=Debug
WorkspacePath          :="/home/uoc/Desktop/ENVIAR TODO OK/UOC2020_2"
ProjectPath            :="/home/uoc/Desktop/ENVIAR TODO OK/UOC2020_2/UOCProgrammeEC"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=uoc
Date                   :=12/05/21
CodeLitePath           :=/home/uoc/.codelite
LinkerName             :=gcc
SharedObjectLinkerName :=gcc -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=../bin/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="UOCProgrammeEC.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -lm
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)./test/include $(IncludeSwitch)../UOCCovid19Vaccine/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)UOCCovid19Vaccine 
ArLibs                 :=  "UOCCovid19Vaccine" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)../lib 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := gcc
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/test_src_test_pr3.c$(ObjectSuffix) $(IntermediateDirectory)/test_src_test_suit.c$(ObjectSuffix) $(IntermediateDirectory)/src_main.c$(ObjectSuffix) $(IntermediateDirectory)/test_src_test_pr2.c$(ObjectSuffix) $(IntermediateDirectory)/test_src_utils.c$(ObjectSuffix) $(IntermediateDirectory)/test_src_test_pr1.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d "../.build-debug/UOCCovid19Vaccine" $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

"../.build-debug/UOCCovid19Vaccine":
	@$(MakeDirCommand) "../.build-debug"
	@echo stam > "../.build-debug/UOCCovid19Vaccine"




MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/test_src_test_pr3.c$(ObjectSuffix): test/src/test_pr3.c $(IntermediateDirectory)/test_src_test_pr3.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/uoc/Desktop/ENVIAR TODO OK/UOC2020_2/UOCProgrammeEC/test/src/test_pr3.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/test_src_test_pr3.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/test_src_test_pr3.c$(DependSuffix): test/src/test_pr3.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/test_src_test_pr3.c$(ObjectSuffix) -MF$(IntermediateDirectory)/test_src_test_pr3.c$(DependSuffix) -MM test/src/test_pr3.c

$(IntermediateDirectory)/test_src_test_pr3.c$(PreprocessSuffix): test/src/test_pr3.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/test_src_test_pr3.c$(PreprocessSuffix) test/src/test_pr3.c

$(IntermediateDirectory)/test_src_test_suit.c$(ObjectSuffix): test/src/test_suit.c $(IntermediateDirectory)/test_src_test_suit.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/uoc/Desktop/ENVIAR TODO OK/UOC2020_2/UOCProgrammeEC/test/src/test_suit.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/test_src_test_suit.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/test_src_test_suit.c$(DependSuffix): test/src/test_suit.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/test_src_test_suit.c$(ObjectSuffix) -MF$(IntermediateDirectory)/test_src_test_suit.c$(DependSuffix) -MM test/src/test_suit.c

$(IntermediateDirectory)/test_src_test_suit.c$(PreprocessSuffix): test/src/test_suit.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/test_src_test_suit.c$(PreprocessSuffix) test/src/test_suit.c

$(IntermediateDirectory)/src_main.c$(ObjectSuffix): src/main.c $(IntermediateDirectory)/src_main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/uoc/Desktop/ENVIAR TODO OK/UOC2020_2/UOCProgrammeEC/src/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_main.c$(DependSuffix): src/main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_main.c$(DependSuffix) -MM src/main.c

$(IntermediateDirectory)/src_main.c$(PreprocessSuffix): src/main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_main.c$(PreprocessSuffix) src/main.c

$(IntermediateDirectory)/test_src_test_pr2.c$(ObjectSuffix): test/src/test_pr2.c $(IntermediateDirectory)/test_src_test_pr2.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/uoc/Desktop/ENVIAR TODO OK/UOC2020_2/UOCProgrammeEC/test/src/test_pr2.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/test_src_test_pr2.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/test_src_test_pr2.c$(DependSuffix): test/src/test_pr2.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/test_src_test_pr2.c$(ObjectSuffix) -MF$(IntermediateDirectory)/test_src_test_pr2.c$(DependSuffix) -MM test/src/test_pr2.c

$(IntermediateDirectory)/test_src_test_pr2.c$(PreprocessSuffix): test/src/test_pr2.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/test_src_test_pr2.c$(PreprocessSuffix) test/src/test_pr2.c

$(IntermediateDirectory)/test_src_utils.c$(ObjectSuffix): test/src/utils.c $(IntermediateDirectory)/test_src_utils.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/uoc/Desktop/ENVIAR TODO OK/UOC2020_2/UOCProgrammeEC/test/src/utils.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/test_src_utils.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/test_src_utils.c$(DependSuffix): test/src/utils.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/test_src_utils.c$(ObjectSuffix) -MF$(IntermediateDirectory)/test_src_utils.c$(DependSuffix) -MM test/src/utils.c

$(IntermediateDirectory)/test_src_utils.c$(PreprocessSuffix): test/src/utils.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/test_src_utils.c$(PreprocessSuffix) test/src/utils.c

$(IntermediateDirectory)/test_src_test_pr1.c$(ObjectSuffix): test/src/test_pr1.c $(IntermediateDirectory)/test_src_test_pr1.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/uoc/Desktop/ENVIAR TODO OK/UOC2020_2/UOCProgrammeEC/test/src/test_pr1.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/test_src_test_pr1.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/test_src_test_pr1.c$(DependSuffix): test/src/test_pr1.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/test_src_test_pr1.c$(ObjectSuffix) -MF$(IntermediateDirectory)/test_src_test_pr1.c$(DependSuffix) -MM test/src/test_pr1.c

$(IntermediateDirectory)/test_src_test_pr1.c$(PreprocessSuffix): test/src/test_pr1.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/test_src_test_pr1.c$(PreprocessSuffix) test/src/test_pr1.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


