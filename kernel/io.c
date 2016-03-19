// no <stdio> :(

unsigned char* row_address(unsigned char l) {
    return (unsigned char*)0xC000 + ((l / 8) * 80) + ((l % 8) * 2048)
}

int main(int argc, char *argv[]) {
    
}
