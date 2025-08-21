# Denote that the targets are not files and suppress command echoing
.PHONY: bin run
.SILENT:

# Binary and source directories
BIN_DIR = bin
SRC_DIR = .

# Create the binary directory if it doesn't exist
${BIN_DIR}:
	mkdir -p ${BIN_DIR}

udp: ${BIN_DIR}
	clang -o ${BIN_DIR}/udp ${SRC_DIR}/udp.c

run: ${SRC_DIR}/udp
	./${BIN_DIR}/udp
	
reciever: ${SRC_DIR}/reciever.c
	clang -o ${BIN_DIR}/reciever ${SRC_DIR}/reciever.c
	./${BIN_DIR}/reciever

sender: ${SRC_DIR}/sender.c
	clang -o ${BIN_DIR}/sender ${SRC_DIR}/sender.c
	./${BIN_DIR}/sender