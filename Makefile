
PLAT ?= LINUX
TYPE ?= DEBUG
TEST ?= OFF



DEPS_BUILD_DIR=build_deps
DEPS_CMAKE=cmake/deps/
DEPS=$(foreach dir,$(DEPS_CMAKE),$(wildcard $(dir)*/*.txt))
DepNameTmp=


define buildDeps
	@-rm -rf $1
	@mkdir -p $1
	@printf "%-8s %s %s %s\n" "[BUILD]" $2 "[TO]" $1
	$(if $(filter $(PLAT),WINDOWS),@cd $1 && cmake $2 -G "Visual Studio 16 2019" -A x64 -D BUILD_OUTPUT_PATH=$1)
	$(if $(filter $(PLAT),LINUX),@cd $1 && cmake $2 -G "Unix Makefiles" -D CMAKE_C_COMPILER=gcc-11 -D CMAKE_CXX_COMPILER=gcc-11 -D BUILD_OUTPUT_PATH=$1)
	$(if $(filter $(PLAT),MACOS),@cd $1 && cmake $2 -G "Unix Makefiles" -D BUILD_OUTPUT_PATH=$1)
	@cd $1 && cmake --build . --config Release
endef



deps:
	@printf "%-8s %s\n" "[CMAKE]" $(DEPS)
	@$(foreach dir,$(DEPS),$(call buildDeps,$(DEPS_BUILD_DIR)/$(basename $(notdir $(patsubst %/,%,$(dir $(dir))).txt)),../../$(dir $(dir))))




rm_submod:
# 清空模块目录
	@-git submodule deinit -f ${MOD_NAME}
# 删除.gitmodules中的模块信息
	@-git rm -r --cached ${MOD_NAME}
# 清理.gitmodules!!!
# 删除目录
	@-sed -i "\#${MOD_NAME}#,+5d" .gitmodules
	@-rm -rf .git/modules/${MOD_NAME}
	@-rm -rf ${MOD_NAME}


run: build
	@./bin/sdl_game
# or run: MESA_GL_VERSION_OVERRIDE=4.6 ./bin/pangu



push:
	@git add -A && git commit -m "update" && git push origin master

pull:
	@-git pull
# @-git pull --recurse-submodules
	@-git submodule sync --recursive
	@-git submodule update --init --recursive


build:
	@rm -rf build
	@mkdir -p build
ifeq ($(PLAT),WINDOWS)
	@cd build && cmake .. -G "Visual Studio 16 2019" -A x64 -DTEST_APP=${TEST}
endif
ifeq ($(PLAT),LINUX)
	@cd build && cmake .. -G "Unix Makefiles" -D CMAKE_C_COMPILER=gcc-11 -D CMAKE_CXX_COMPILER=g++-11  -DTEST_APP=${TEST}
endif
ifeq ($(PLAT),MACOS)
	@cd build && cmake .. -G "Unix Makefiles"  -DTEST_APP=${TEST}
endif

ifeq (${TYPE},DEBUG)
	@cd build && cmake --build . --config Debug
endif
ifeq (${TYPE},RELEASE)
	@cd build && cmake --build . --config Release
endif
ifeq (${TYPE},RELDEBINFO)
	@cd build && cmake --build . --config ReleaseDebInfo
endif



BUILD_TEST_DIR=build_test
TEST_CMAKE_DIR=../tests


test:
	@rm -rf ${BUILD_TEST_DIR}
	@mkdir -p ${BUILD_TEST_DIR}
ifeq ($(PLAT),WINDOWS)
	@cd ${BUILD_TEST_DIR} && cmake ${TEST_CMAKE_DIR} -G "Visual Studio 16 2019" -A x64 -DTEST_APP=${TEST}
endif
ifeq ($(PLAT),LINUX)
	@cd ${BUILD_TEST_DIR} && cmake ${TEST_CMAKE_DIR} -G "Unix Makefiles" -D CMAKE_C_COMPILER=gcc-11 -D CMAKE_CXX_COMPILER=g++-11  -DTEST_APP=${TEST}
endif
ifeq ($(PLAT),MACOS)
	@cd ${BUILD_TEST_DIR} && cmake ${TEST_CMAKE_DIR} -G "Unix Makefiles"  -DTEST_APP=${TEST}
endif

ifeq (${TYPE},DEBUG)
	@cd ${BUILD_TEST_DIR} && cmake --build . --config Debug
endif
ifeq (${TYPE},RELEASE)
	@cd ${BUILD_TEST_DIR} && cmake --build . --config Release
endif
ifeq (${TYPE},RELDEBINFO)
	@cd ${BUILD_TEST_DIR} && cmake --build . --config ReleaseDebInfo
endif



.PHONY: rm_submod run build pull test run push deps
