#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Mutex.o \
	${OBJECTDIR}/Thread.o \
	${OBJECTDIR}/dataQueue.o \
	${OBJECTDIR}/getCell.o \
	${OBJECTDIR}/lineProcess.o \
	${OBJECTDIR}/loadsummary.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/mongo.o \
	${OBJECTDIR}/mysql_loader.o \
	${OBJECTDIR}/readFile.o \
	${OBJECTDIR}/readQueue.o \
	${OBJECTDIR}/writeDb.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/include/boost/lib -lpthread -lboost_iostreams -L/usr/local/lib/libmongocxx.so -lbsoncxx -lmongocxx -lboost_date_time -L/usr/lib64 -lmysqlcppconn

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk cdr_loader

cdr_loader: ${OBJECTFILES}
	g++ -o cdr_loader ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Mutex.o: Mutex.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/mongocxx/v_noabi -I/usr/include/mysql -I/usr/include/mysql-cppconn-8/jdbc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Mutex.o Mutex.cpp

${OBJECTDIR}/Thread.o: Thread.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/mongocxx/v_noabi -I/usr/include/mysql -I/usr/include/mysql-cppconn-8/jdbc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Thread.o Thread.cpp

${OBJECTDIR}/dataQueue.o: dataQueue.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/mongocxx/v_noabi -I/usr/include/mysql -I/usr/include/mysql-cppconn-8/jdbc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/dataQueue.o dataQueue.cpp

${OBJECTDIR}/getCell.o: getCell.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/mongocxx/v_noabi -I/usr/include/mysql -I/usr/include/mysql-cppconn-8/jdbc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/getCell.o getCell.cpp

${OBJECTDIR}/lineProcess.o: lineProcess.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/mongocxx/v_noabi -I/usr/include/mysql -I/usr/include/mysql-cppconn-8/jdbc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lineProcess.o lineProcess.cpp

${OBJECTDIR}/loadsummary.o: loadsummary.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/mongocxx/v_noabi -I/usr/include/mysql -I/usr/include/mysql-cppconn-8/jdbc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/loadsummary.o loadsummary.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/mongocxx/v_noabi -I/usr/include/mysql -I/usr/include/mysql-cppconn-8/jdbc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/mongo.o: mongo.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/mongocxx/v_noabi -I/usr/include/mysql -I/usr/include/mysql-cppconn-8/jdbc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mongo.o mongo.cpp

${OBJECTDIR}/mysql_loader.o: mysql_loader.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/mongocxx/v_noabi -I/usr/include/mysql -I/usr/include/mysql-cppconn-8/jdbc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mysql_loader.o mysql_loader.cpp

${OBJECTDIR}/readFile.o: readFile.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/mongocxx/v_noabi -I/usr/include/mysql -I/usr/include/mysql-cppconn-8/jdbc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/readFile.o readFile.cpp

${OBJECTDIR}/readQueue.o: readQueue.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/mongocxx/v_noabi -I/usr/include/mysql -I/usr/include/mysql-cppconn-8/jdbc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/readQueue.o readQueue.cpp

${OBJECTDIR}/writeDb.o: writeDb.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/mongocxx/v_noabi -I/usr/include/mysql -I/usr/include/mysql-cppconn-8/jdbc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/writeDb.o writeDb.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
