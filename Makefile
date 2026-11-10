
CC      = clang
# CFLAGS  = -std=c99 -g -Wall -Wextra -Werror
CFLAGS  = -std=c99 -g -Wall -Wextra
DISTDIR = dist
EXDIR = examples

run-%: $(DISTDIR)/%
	./$<

tidyrun-%: tidy $(DISTDIR)/%
	./$(DISTDIR)/$*

$(DISTDIR)/%: $(EXDIR)/%.c $(DISTDIR)
	$(CC) $(CFLAGS) $< -o $@

$(DISTDIR):
	@mkdir -p $(DISTDIR)

tidy:
	rm -rf $(DISTDIR)

.PHONY: tidy

