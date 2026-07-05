CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LDFLAGS = -lz -lcrypto

SRCS = src/main.cpp src/utils.cpp src/git_objects.cpp src/git_commands.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = mygit

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
