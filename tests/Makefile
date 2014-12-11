default: md run-tests clean

md:
	mkdir out
	mkdir diff

clean:
	rm -rf out
	rm -rf diff

test:
	bash ./final_test.sh ../bin/hf

run-tests:
	bash ./test.sh ../bin/hf
