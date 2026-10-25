volatile unsigned int initialized_counter = 7;
volatile unsigned int zero_counter;

int main(void)
{
    zero_counter = initialized_counter;

    while (1) {
    }
}
