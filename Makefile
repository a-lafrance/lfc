# Global directories
INCLUDE_DIR = include
SRC_DIR = src
TARGET_DIR = target

CC = clang # FIXME: this should really be architecture-specific

BASE_CFLAGS = -g -I../include
LFC_CFLAGS = $(BASE_CFLAGS) -c
TESTS_CFLAGS = $(BASE_CFLAGS) -L. -llfc -o tests

# TODO: this needs a lot of work to be as sophisticated as it should be

.PHONY: tests collections utils clean

all: liblfc.a

liblfc.a: $(TARGET_DIR) collections utils
	ar -rc -v $(TARGET_DIR)/$@ $(TARGET_DIR)/*.o # stitch all the obj files into an archive
	-rm $(TARGET_DIR)/*.o # remove the obj files

tests: $(TARGET_DIR) liblfc.a
	cd $(TARGET_DIR) && $(CC) $(TESTS_CFLAGS)                    \
		../$(SRC_DIR)/lfc/collections/tests/array_tests.c        \
		../$(SRC_DIR)/lfc/collections/tests/linkedlist_tests.c   \
		../$(SRC_DIR)/lfc/collections/tests/map_tests.c          \
		../$(SRC_DIR)/lfc/collections/tests/set_tests.c          \
		../$(SRC_DIR)/lfc/collections/tests/str_tests.c          \
		../$(SRC_DIR)/lfc/collections/tests/vector_tests.c       \
		../$(SRC_DIR)/lfc/utils/tests/hash_tests.c               \
		../$(SRC_DIR)/tests/utils.c                              \
		../$(SRC_DIR)/tests/main.c

collections: $(TARGET_DIR)
	cd $(TARGET_DIR) && $(CC) $(LFC_CFLAGS)          \
		../$(SRC_DIR)/lfc/collections/array.c        \
		../$(SRC_DIR)/lfc/collections/linkedlist.c   \
		../$(SRC_DIR)/lfc/collections/map.c          \
		../$(SRC_DIR)/lfc/collections/set.c          \
		../$(SRC_DIR)/lfc/collections/str.c          \
		../$(SRC_DIR)/lfc/collections/vector.c       \
		../$(SRC_DIR)/internals/collections/__mapbucket.c

utils: $(TARGET_DIR)
	cd $(TARGET_DIR) && $(CC) $(LFC_CFLAGS)  \
		../$(SRC_DIR)/lfc/utils/convert.c    \
		../$(SRC_DIR)/lfc/utils/hash.c       \
		../$(SRC_DIR)/lfc/utils/mem.c        \
		../$(SRC_DIR)/lfc/utils/pair.c

$(TARGET_DIR):
	mkdir -p $@

clean:
	-rm -rf target
