#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

const uint32_t s[] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

const uint32_t K[] = { /* Constantes predefinidas */ };

typedef struct {
    uint32_t h[4];
} MD5_CTX;

void md5_init(MD5_CTX *ctx) {
    ctx->h[0] = 0x67452301;
    ctx->h[1] = 0xefcdab89;
    ctx->h[2] = 0x98badcfe;
    ctx->h[3] = 0x10325476;
}

void md5_process(MD5_CTX *ctx, uint8_t *chunk) {
    uint32_t a, b, c, d, f, g, temp, m[16];
    for (int i = 0; i < 16; i++) {
        m[i] = (chunk[i * 4]) | (chunk[i * 4 + 1] << 8) |
               (chunk[i * 4 + 2] << 16) | (chunk[i * 4 + 3] << 24);
    }

    a = ctx->h[0];
    b = ctx->h[1];
    c = ctx->h[2];
    d = ctx->h[3];

    for (int i = 0; i < 64; i++) {
        if (i < 16) {
            f = (b & c) | (~b & d);
            g = i;
        } else if (i < 32) {
            f = (d & b) | (~d & c);
            g = (5 * i + 1) % 16;
        } else if (i < 48) {
            f = b ^ c ^ d;
            g = (3 * i + 5) % 16;
        } else {
            f = c ^ (b | ~d);
            g = (7 * i) % 16;
        }

        temp = d;
        d = c;
        c = b;
        b = b + LEFTROTATE((a + f + K[i] + m[g]), s[i]);
        a = temp;
    }

    ctx->h[0] += a;
    ctx->h[1] += b;
    ctx->h[2] += c;
    ctx->h[3] += d;
}

void md5(uint8_t *msg, size_t len, uint8_t *digest) {
    MD5_CTX ctx;
    md5_init(&ctx);

    uint64_t bit_len = len * 8;
    msg[len] = 0x80;
    len++;

    while (len % 64 != 56) {
        msg[len++] = 0;
    }

    memcpy(msg + len, &bit_len, 8);
    len += 8;

    for (size_t i = 0; i < len; i += 64) {
        md5_process(&ctx, msg + i);
    }

    memcpy(digest, ctx.h, 16);
}

int main() {
    char input[256], modified_input[300];
    uint8_t digest[16];
    int counter;

    while (1) {
        printf("Digite uma string (ou 'sair' para finalizar): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "sair") == 0) {
            break;
        }

        counter = 0;
        while (1) {
            snprintf(modified_input, sizeof(modified_input), "%s%d", input, counter);
            md5((uint8_t *)modified_input, strlen(modified_input), digest);
            if (digest[0] == 0x00) {
                printf("MD5 encontrado: %s -> ", modified_input);
                for (int i = 0; i < 16; i++) {
                    printf("%02x", digest[i]);
                }
                printf("\n");
                break;
            }
            counter++;
        }
    }

    return 0;
}
