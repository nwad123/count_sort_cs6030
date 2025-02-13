BUILD_DIR := build
RESULT_DIR := results
HISTOGRAM_PATH := ./histogram
NAME ?= waddoups

build: build_ 
	cmake --build ${BUILD_DIR}

.PHONY: build_ 
build_: build_dir
	cd $(BUILD_DIR); cmake ..

# Generates a build directory
.PHONY: build_dir
build_dir:
	@mkdir -p $(BUILD_DIR);

# Cleans all build files
.PHONY: clean
clean:
	@echo "Removing build directory (${BUILD_DIR})..."
	@rm -rf ${BUILD_DIR}
	@rm -f ${HISTOGRAM_PATH}
	@rm -rf .cache

# Zips all data together for submitting to canvas
.PHONY: submission
submission: 
	@echo "Zipping together project files..."
	cd ..; \
		tar --exclude='build*' --exclude='.cache*' --exclude='.venv*' \
		--exclude-vcs -cvzf ${NAME}_hw3.tar.gz -C ${CURDIR} .
