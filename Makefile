all : copy_sdl make_the_bouzin

copy_sdl:
	mkdir -p ~/Library/Frameworks
	cp -r corewar_dir/SDL2.framework ~/Library/Frameworks
	cp -r corewar_dir/SDL2_image.framework ~/Library/Frameworks
	cp -r corewar_dir/SDL2_ttf.framework ~/Library/Frameworks

make_the_bouzin: make_printf make_corewar make_asm
	cp corewar_dir/corewar .
	cp asm_dir/asm .

make_corewar:
	make -C corewar_dir/

make_printf:
	make -C ft_printf/

make_asm:
	make -C asm_dir/

clean:
	@make clean -C corewar_dir/
	@make clean -C asm_dir/
	@make clean -C ft_printf/

fclean:
	@rm -f asm corewar
	@make fclean -C corewar_dir/
	@make fclean -C asm_dir/
	@make fclean -C ft_printf/

re: fclean all

.PHONY: clean fclean re make_asm make_printf make_corewar make_the_bouzin copy_sdl
