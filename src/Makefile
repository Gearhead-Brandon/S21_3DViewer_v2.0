EXECUTE = 3DViewer

DIR_INSTALL = out
DIR_BUILD = build

DIR_TEST = unit_tests
DIR_TESTS_BUILD = $(DIR_TEST)/build
TEST_EXE = tests

DIR_REPORT = report
HTML_REPORT = REPORT.html
EXCLUDE_FILES = "unit_tests/*" "app/Model/Components/AffineTransformations/ITransformation/ITransformation.h" \
				"app/Common/FacadeOpResult/*" "app/Model/Components/Figure/*" "app/Model/Components/FileReader/FileReader.h" \
				"app/Model/Components/FileReader/IFileReader/IFileReader.h"
EXCLUDE_REPORT = $(foreach file, $(EXCLUDE_FILES), --exclude $(file)) 

DOC = doc/html

DISTRIBUTION = 3DViewer.tar

all: install

install:
	@mkdir -p ./out/shaders ./out/img
	@find ./app/ -name "*.glsl" -exec cp {} ./out/shaders \;
	@find ./app/View/Components/Style/images/ -name "*.jpeg" -exec cp {} ./out/img \;
	cd ./$(DIR_BUILD) && cmake .. && make && mv $(EXECUTE) ../$(DIR_INSTALL)
	make run

run:
	cd $(DIR_INSTALL) && ./$(EXECUTE)

uninstall:
	@rm -rf ./$(DIR_INSTALL)\

tests:
	cd ./$(DIR_TESTS_BUILD) && cmake .. && make && mv $(TEST_EXE) ..
	cd ./$(DIR_TEST) && ./$(TEST_EXE)

gcov_report: tests
	@mkdir -p $(DIR_REPORT)
	@find ./$(DIR_TESTS_BUILD)/CMakeFiles \( -name "*.gcno" -o -name "*.gcda"  \) -exec mv {} $(DIR_REPORT)/ \;
	~/.local/bin/gcovr $(DIR_REPORT)/ $(EXCLUDE_REPORT) --html --html-details -o $(HTML_REPORT)
	@make move_report

move_report:
	@mv *.html *.css $(DIR_REPORT)

peer: gcov_report
	@open $(DIR_REPORT)/$(HTML_REPORT)

dvi:
#   doxygen ./$(DOC)/Doxyfile
#	@google-chrome ./$(DOC)/index.html

dist:
	@if [ -d "$(DIR_INSTALL)" ]; then \
		(cd $(DIR_INSTALL) && tar -cf $(DISTRIBUTION) . && mv $(DISTRIBUTION) ../); \
	else \
		echo "Directory $(DIR_INSTALL) does not exist."; \
	fi

clean:
	@rm -rf ./$(DIR_BUILD)/* ./$(DIR_BUILD)/.cmake/
	@rm -rf ./$(DIR_TESTS_BUILD)/*
	@rm -rf ./$(DIR_TEST)/tests $(DIR_REPORT)

rebuild: clean uninstall install