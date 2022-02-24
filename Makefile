NAME			= ft_container_tester
# ==============================================================================

# SRCS =========================================================================
SOURCES_FOLDER	= ./tester/

SOURCES			=	main.cpp \
					tester.cpp \
					tester_map.cpp \
					tester_vector.cpp \
					tester_stack.cpp
					
# ==============================================================================

# INCLUDES =====================================================================
INCLUDE 		= ./tester/tester.hpp
# ==============================================================================

# FLAGS ========================================================================
FLAGS 			= -Wall -Wextra -Werror --std=c++98
# ==============================================================================

# OBJECTS ======================================================================
OBJECTS_FOLDER 	= ./tester/objects/

OBJECT			= $(SOURCES:.cpp=.o)
OBJECTS		 	= $(addprefix $(OBJECTS_FOLDER), $(OBJECT));
# ==============================================================================

# TESTER =======================================================================

$(OBJECTS_FOLDER)%.o :	$(SOURCES_FOLDER)%.cpp	$(INCLUDE) 
	@mkdir -p	$(OBJECTS_FOLDER)
	@echo "Compiling: $<"
	@clang++ $(FLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	@clang++ $(FLAGS) -o $(NAME) $(OBJECTS)

all: $(NAME)

clean:
	@echo "Cleaning: $(OBJECTS_FOLDER)"
	@rm -rf $(OBJECTS_FOLDER)
	@echo "Cleaning: ./tester/vectors_output"
	@rm -rf ./tester/vectors_output
	@echo "Cleaning: ./tester/stacks_output"
	@rm -rf ./tester/stacks_output
	@echo "Cleaning: ./tester/maps_output"
	@rm -rf ./tester/maps_output

fclean: clean
	@echo "Cleaning: $(NAME)"
	@rm -f $(NAME)

re: fclean all
# ==============================================================================

# SUP ==========================================================================

run: $(NAME)
	@./$(NAME)

