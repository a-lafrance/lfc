INCLUDE_DIR = include
SRC_DIR = src
TARGET_DIR = target
TESTS_DIR = tests/src

CC = clang
CFLAGS = -g -c -I../include
TESTS_CFLAGS = -I../include -I../tests/include -L. -llfc -o tests

# TODO: audit this build stuff because what if globs are bad

liblfc:
	$(MAKE) proper_include collections utils # build each part of the lib
	ar -rc -v $(TARGET_DIR)/$@.a $(TARGET_DIR)/*.o # stitch all the obj files into an archive
	-rm $(TARGET_DIR)/*.o # remove the obj files
	$(MAKE) undo_proper_include

lfc_tests:
	$(MAKE) liblfc proper_include
	cd $(TARGET_DIR) && $(CC) $(TESTS_CFLAGS)           \
		../$(TESTS_DIR)/collections/array_tests.c       \
		../$(TESTS_DIR)/collections/linkedlist_tests.c  \
		../$(TESTS_DIR)/collections/set_tests.c         \
		../$(TESTS_DIR)/collections/str_tests.c         \
		../$(TESTS_DIR)/collections/vector_tests.c      \
		../$(TESTS_DIR)/utils/hash_tests.c              \
		../$(TESTS_DIR)/utils.c                         \
		../$(TESTS_DIR)/main.c
	$(MAKE) undo_proper_include

collections:
	mkdir -p $(TARGET_DIR)
	cd $(TARGET_DIR) && $(CC) $(CFLAGS)         \
		../$(SRC_DIR)/collections/array.c       \
		../$(SRC_DIR)/collections/linkedlist.c  \
		../$(SRC_DIR)/collections/map.c         \
		../$(SRC_DIR)/collections/set.c         \
		../$(SRC_DIR)/collections/str.c         \
		../$(SRC_DIR)/collections/vector.c

utils:
	mkdir -p $(TARGET_DIR)
	cd $(TARGET_DIR) && $(CC) $(CFLAGS)  \
		../$(SRC_DIR)/utils/hash.c       \
		../$(SRC_DIR)/utils/mem.c        \
		../$(SRC_DIR)/utils/pair.c

proper_include:
	mkdir -p $(INCLUDE_DIR)/lfc
	mv $(INCLUDE_DIR)/collections $(INCLUDE_DIR)/lfc
	mv $(INCLUDE_DIR)/utils $(INCLUDE_DIR)/lfc

# FIXME: this is ridiculously inefficient for large projects so there has to be a better way
#       stitch this together right? yikes
undo_proper_include:
	mv $(INCLUDE_DIR)/lfc/collections $(INCLUDE_DIR)
	mv $(INCLUDE_DIR)/lfc/utils $(INCLUDE_DIR)
	-rm -rf $(INCLUDE_DIR)/lfc

clean:
	-rm -rf target
