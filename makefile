# variables 
SRC_DIR = apps/msh/src
SRC = $(SRC_DIR)/minishell.c 
OUT = $(SRC_DIR)/msh

# Targets
all: $(OUT)

$(OUT): $(SRC)
	gcc $< -o $@

msh: 
	$(SRC_DIR)/msh
	
clean: 
	rm -f $(OUT)
