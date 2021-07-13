INCLUDE_DIR = include/lfc
SRC_DIR = src/lfc
TARGET_DIR = target

CC = clang
CFLAGS = -c -I../include

# TODO: audit this build stuff because what if globs are bad

liblfc:
	$(MAKE) collections utils # build each part of the lib
	ar -rc $(TARGET_DIR)/$@.a $(TARGET_DIR)/*.o # stitch all the obj files into an archive
	rm $(TARGET_DIR)/*.o # remove the obj files

collections:
	mkdir -p $(TARGET_DIR)
	cd $(TARGET_DIR) && $(CC) $(CFLAGS)        \
		../$(SRC_DIR)/collections/array.c      \
		../$(SRC_DIR)/collections/linkedlist.c \
		../$(SRC_DIR)/collections/set.c

utils:
	mkdir -p $(TARGET_DIR)
	cd $(TARGET_DIR) && $(CC) $(CFLAGS) \
		../$(SRC_DIR)/utils/mem.c

clean:
	-rm -rf target
