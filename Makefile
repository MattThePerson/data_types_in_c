.SECONDEXPANSION:
.SECONDARY:
# .PRECIOUS: $(DISTDIR)/%       # keep just the binaries
# .NOTINTERMEDIATE:             # GNU Make 4.4+, also stops Make from chaining implicit rules

CC      = clang
# CFLAGS  = -std=c99 -g -Wall -Wextra -Werror
CFLAGS  = -std=c99 -g -Wall -Wextra
DISTDIR = dist
EXDIR = examples

run-%: $(DISTDIR)/%
	./$<

tidyrun-%: tidy $(DISTDIR)/%
	./$(DISTDIR)/$*

# Single-file example: examples/foo.c -> dist/foo
$(DISTDIR)/%: $(EXDIR)/%.c | $(DISTDIR)
	$(CC) $(CFLAGS) $< -o $@

# Folder example: examples/foo/*.c -> dist/foo
$(DISTDIR)/%: $$(wildcard $(EXDIR)/$$*/*.c) | $(DISTDIR)
	$(CC) $(CFLAGS) $^ -o $@

$(DISTDIR):
	@mkdir -p $(DISTDIR)

tidy:
	rm -rf $(DISTDIR)

.PHONY: tidy

