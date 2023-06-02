#include "client.h"


void initialize_client(struct client *my_client)
{
    // Initialize client: description
    int ret;
    char buff[DESC_MAX_SIZE];
    ret = get_client_desc("Enter client desc>\n\t", buff, sizeof(buff));
    if (ret == DESC_NO_INPUT) {
        printf("\nNo input\n");
        return;
    }
    if (ret == DESC_TOO_LONG) {
        printf("Client description too long [%s]\n", buff);
        return;
    }
    for (int i = 0; i < DESC_MAX_SIZE; i++)
        my_client->about[i] = buff[i];

    // Initialize client: n
    int n = -1;
    printf("n> ");
    scanf("%d", &n);
    while (n < MIN_N_VALUE || n > MAX_N_VALUE) {
        printf("Invalid value for n, try again...\n");
        printf("n = ");
        scanf("%d", &n);
    }
    my_client->n = n;

    // Initialize client: value
    calculate_value(my_client);
}

int get_client_desc(char* prmpt, char* buff, size_t sz)
{
    int ch;
    int extra;

    if (prmpt != NULL) {
        printf("%s", prmpt);
        fflush(stdout);
    }
    if (fgets(buff, sz, stdin) == NULL)
        return DESC_NO_INPUT;

    if (buff[strlen(buff) - 1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? DESC_TOO_LONG : DESC_OK;
    }

    buff[strlen(buff) - 1] = '\0';
    return DESC_OK;
}

void calculate_value(struct client* my_client)
{
    float radian[ARRAY_OF_VALUES_SIZE];

    radian[0] = 0;
    for (int i = 1; i < ARRAY_OF_VALUES_SIZE; i++)
        radian[i] = radian[i - 1] + RADIAN_INC_FACTOR;

    my_client->value[0] = 0.0;
    for (int i = 1; i < ARRAY_OF_VALUES_SIZE; i++)
        my_client->value[i] = my_client->n * sin(radian[i]);
}
