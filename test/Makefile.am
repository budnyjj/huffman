all-local: setup test tear-down

setup:
	mkdir out
	mkdir diff

tear-down:
	rm -rf out
	rm -rf diff

test:
	bash ./test.sh $(top_builddir)/src/huffman

finaltest:
	bash ./final_test.sh $(top_builddir)/src/huffman
