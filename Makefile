.SECONDEXPANSION:
.SECONDARY:

CC = clang
# CFLAGS  = -std=c99 -g -Wall -Wextra -Werror
CFLAGS = -std=c99 -g
# DEPFLAGS = -MMD -MP
DEPFLAGS =
DISTDIR = dist

# = RUN ======================

# make run/examples/demo_bst
run/%: $(DISTDIR)/%
	./$(DISTDIR)/$* $(ARGS)

cleanrun/%: clean $(DISTDIR)/%
	./$(DISTDIR)/$* $(ARGS)

# = BUILD ====================

# Single file: dist/examples/foo <- examples/foo.c
$(DISTDIR)/%: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DEPFLAGS) $< -o $@

# Folder: dist/examples/foo <- examples/foo/*.c
$(DISTDIR)/%: $$(wildcard %/*.c)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DEPFLAGS) $^ -o $@

# include header deps (written by -MMD)
-include $(shell find dist -name '*.d' 2>/dev/null)

# = MISC =====================

clean:
	rm -rf $(DISTDIR)

.PHONY: clean

