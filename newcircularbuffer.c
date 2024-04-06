#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define N 5 // SETTING THE BUFFER SIZE//

typedef enum // STORING  DIFFERNT DATATYPES //
{
    INT,
    CHAR,
    STRING,
    UINT32,
    UINT64,
    FLOAT,
} DataType;

typedef struct // STORING DATA AND ITS TYPE//
{
    void *buffer;
    DataType type;
} Element;

typedef struct
{
    Element *buffer;
    int front;
    int rear;
    int size;
    DataType type;
} CircularBuffer;

// INITIALIZING THE BUFFER - BY PASSING SIZE AND DATATYPE //
CircularBuffer *InitCircularBuffer(int size, DataType type)
{
    CircularBuffer *cb = (CircularBuffer *)malloc(sizeof(CircularBuffer)); // MEMORY ALLOCATING //
    cb->buffer = (Element *)malloc(size * sizeof(Element));
    cb->front = -1;
    cb->rear = -1;
    cb->size = size;
    cb->type = type;
    return cb;
}

int isFull(CircularBuffer *cb)
{
    return (cb->front == (cb->rear + 1) % cb->size); // WARPPING THE CIRCULARBUFFER WHEN IT IS FULL//
}

int isEmpty(CircularBuffer *cb)
{
    return (cb->front == -1); // ADD DATA FROM FRONT POINTER WHEN BUFFER IS EMPTY//
}

size_t getSizeOfType(DataType type) // DETERMINING THE DATATYPE//
{
    switch (type)
    {
    case INT:
        return sizeof(int);
    case CHAR:
        return sizeof(char);
    case UINT32:
        return sizeof(uint32_t);
    case UINT64:
        return sizeof(uint64_t);
    case FLOAT:
        return sizeof(float);
    default:
        return 0;
    }
}

void addToCircularBuffer(CircularBuffer *cb, void *data, DataType type)
{
    if (isFull(cb))
    {
        printf("Circular buffer is full, overwriting the value\n"); // OVERWRITING THE BUFFER BY MOVING THE FRONT END//
        cb->front = (cb->front + 1) % cb->size;
        if (cb->buffer[cb->front].type == STRING)
        {
            free(cb->buffer[cb->front].buffer);
        }
    }
    if (cb->type != type) // CHECKING THE DATATYPES TO ADD//
    {
        printf("data type is invalid/n");
        return;
    }
    else if (cb->type == UINT32) // CHECKING FOR THE UINT32 VALUES//
    {
        uint32_t *newData = (uint32_t *)malloc(sizeof(uint32_t));
        *newData = *((uint32_t *)data);
        cb->rear = (cb->rear + 1) % cb->size;
        cb->buffer[cb->rear].buffer = newData;
        cb->buffer[cb->rear].type = cb->type;
    }
    else if (cb->type == UINT64) // CHECKING FOR THE UINT64 VALUES//
    {
        uint64_t *newData = (uint64_t *)malloc(sizeof(uint64_t));
        *newData = *((uint64_t *)data);
        cb->rear = (cb->rear + 1) % cb->size;
        cb->buffer[cb->rear].buffer = newData;
        cb->buffer[cb->rear].type = cb->type;
    }
    else if (cb->type == STRING) // CHECKING FOR THE STRING DATA//
    {
        char *newData = strdup((char *)data);
        cb->rear = (cb->rear + 1) % cb->size;
        cb->buffer[cb->rear].buffer = newData;
        cb->buffer[cb->rear].type = cb->type;
    }
    else
    {
        void *newData = malloc(getSizeOfType(cb->type)); // ALLOCTAES MEMORY FOR NEWDATA POINTER USING MALLOC //
        memcpy(newData, data, getSizeOfType(cb->type));  // COPYING THE DATA INTO NEWDATA //
        cb->rear = (cb->rear + 1) % cb->size;
        cb->buffer[cb->rear].buffer = newData;
        cb->buffer[cb->rear].type = cb->type;
    }
    if (cb->front == -1)
        cb->front = cb->rear;
}

void *removeFromCircularBuffer(CircularBuffer *cb) // removing the data from buffer//
{
    if (isEmpty(cb))
    {
        printf("Circular buffer is empty\n");
        return NULL;
    }

    void *data = cb->buffer[cb->front].buffer;
    cb->front = (cb->front + 1) % cb->size;

    if (cb->front == (cb->rear + 1) % cb->size) // OVERWRITING THE VALUES //
    {
        cb->front = -1;
        cb->rear = -1;
    }

    return data;
}

void printCircularBuffer(CircularBuffer *cb)
{
    if (isEmpty(cb))
    {
        printf("Circular buffer is empty\n");
        return;
    }

    int i = cb->front;
    while (1)
    {
        Element buffer = cb->buffer[i];
        switch (buffer.type)
        {
        case INT:
            printf("%d ", *((int *)buffer.buffer));
            break;
        case FLOAT:
            printf("%.3f ", *((float *)buffer.buffer));
            break;
        case CHAR:
            printf("%c ", *((char *)buffer.buffer));
            break;
        case STRING:
            printf("%s ", (char *)buffer.buffer);
            break;
        case UINT64:
            printf("%u ", *((uint64_t *)buffer.buffer));
            break;
        case UINT32:
            printf("%u ", *((uint32_t *)buffer.buffer));
            break;
        default:
            printf("Unknown data type\n");
        }

        i = (i + 1) % cb->size;

        if (i == (cb->rear + 1) % cb->size)
            break;
    }
    printf("\n");
}
void freeCircularBuffer(CircularBuffer *cb)
{
    free(cb->buffer);
    free(cb);
}

int main()
{                 
                        //  INT INPUT VALUES//
    CircularBuffer *cb = InitCircularBuffer(N, INT); // INT VALUES //

    int int_data = 123;
    addToCircularBuffer(cb, &int_data, INT);
    printCircularBuffer(cb);

    int int_data0 = 1234;
    addToCircularBuffer(cb, &int_data0, INT);
    printCircularBuffer(cb);

    int int_data1 = 12345;
    addToCircularBuffer(cb, &int_data1, INT);
    printCircularBuffer(cb);

    int int_data2 = 123456;
    addToCircularBuffer(cb, &int_data2, INT);
    printCircularBuffer(cb);

    int int_data3 = 1234567;
    addToCircularBuffer(cb, &int_data3, INT);
    printCircularBuffer(cb);

    int int_data4 = 12345678;
    addToCircularBuffer(cb, &int_data4, INT);
    printCircularBuffer(cb);

    int int_data5 = 123456789;
    addToCircularBuffer(cb, &int_data5, INT);
    printCircularBuffer(cb);

    int int_data6 = 1234567890;
    addToCircularBuffer(cb, &int_data6, INT);
    printCircularBuffer(cb);

    int int_data7 = 987654321;
    addToCircularBuffer(cb, &int_data7, INT);
    printCircularBuffer(cb);

                    //      UINT32 INPUT VALUES //

        // CircularBuffer *cb = InitCircularBuffer(N, UINT32);  // UINT32 VALUES //

        // uint32_t uint32_data = 123;
        // addToCircularBuffer(cb, &uint32_data,UINT32);
        // printf("value added to circular buffer: %u\n", *((uint32_t *)cb->buffer[cb->rear].buffer));
        //      printCircularBuffer(cb);

        // uint32_t uint32_data0 = 1234;
        // addToCircularBuffer(cb, &uint32_data0,UINT32);
        // printf("value added to circular buffer: %u\n", *((uint32_t *)cb->buffer[cb->rear].buffer));
        //      printCircularBuffer(cb);

        // uint32_t uint32_data1 = 12345;
        // addToCircularBuffer(cb, &uint32_data1,UINT32);
        // printf("value added to circular buffer: %u\n", *((uint32_t *)cb->buffer[cb->rear].buffer));
        //      printCircularBuffer(cb);

        // uint32_t uint32_data2 = 123456;
        // addToCircularBuffer(cb, &uint32_data2,UINT32);
        // printf("value added to circular buffer: %u\n", *((uint32_t *)cb->buffer[cb->rear].buffer));
        //      printCircularBuffer(cb);

        // uint32_t uint32_data3 = 1234567;
        // addToCircularBuffer(cb, &uint32_data3,UINT32);
        // printf("value added to circular buffer: %u\n", *((uint32_t *)cb->buffer[cb->rear].buffer));
        //      printCircularBuffer(cb);

        // uint32_t uint32_data4 = 12345678;
        // addToCircularBuffer(cb, &uint32_data4,UINT32);
        // printf("value added to circular buffer: %u\n", *((uint32_t *)cb->buffer[cb->rear].buffer));
        //      printCircularBuffer(cb);

        // uint32_t uint32_data5 = 123456789;
        // addToCircularBuffer(cb, &uint32_data5,UINT32);
        // printf("value added to circular buffer: %u\n", *((uint32_t *)cb->buffer[cb->rear].buffer));
        //      printCircularBuffer(cb);

        // uint32_t uint32_data6 = 1234567890;
        // addToCircularBuffer(cb, &uint32_data6,UINT32);
        // printf("value added to circular buffer: %u\n", *((uint32_t *)cb->buffer[cb->rear].buffer));
        //      printCircularBuffer(cb);

        // uint32_t uint32_data7 = 987654321;
        // addToCircularBuffer(cb, &uint32_data7,UINT32);
        // printf("value added to circular buffer: %u\n", *((uint32_t *)cb->buffer[cb->rear].buffer));
        //      printCircularBuffer(cb);

                         //string INPUT values//

    // CircularBuffer *cb = InitCircularBuffer(N, STRING); // string values//

    // char *string_data = "Hello";
    // addToCircularBuffer(cb, string_data,STRING);
    // // printf("value added to circular buffer: %s\n", (char *)cb->buffer[cb->rear].buffer);
    // printCircularBuffer(cb);

    // char *string_data2 = "hello1";
    // addToCircularBuffer(cb, string_data2,STRING);
    // // printf("value added to circular buffer: %s\n", (char *)cb->buffer[cb->rear].buffer);
    // printCircularBuffer(cb);

    // char *string_data3 = "hello2";
    // addToCircularBuffer(cb, string_data3,STRING);
    // // printf("value added to circular buffer: %s\n", (char *)cb->buffer[cb->rear].buffer);
    // printCircularBuffer(cb);

    // char *string_data4 = "hello3";
    // addToCircularBuffer(cb, string_data4,STRING);
    // // printf("value added to circular buffer: %s\n", (char *)cb->buffer[cb->rear].buffer);
    // printCircularBuffer(cb);

    // char *string_data5 = "hello4";
    // addToCircularBuffer(cb, string_data5,STRING);
    // // printf("value added to circular buffer: %s\n", (char *)cb->buffer[cb->rear].buffer);
    // printCircularBuffer(cb);

    // char *string_data6 = "hello5";
    // addToCircularBuffer(cb, string_data6,STRING);
    // // printf("value added to circular buffer: %s\n", (char *)cb->buffer[cb->rear].buffer);
    //    printCircularBuffer(cb);

    // char *string_data7 = "hello6";
    // addToCircularBuffer(cb, string_data7,STRING);
    // // printf("value added to circular buffer: %s\n", (char *)cb->buffer[cb->rear].buffer);
    //    printCircularBuffer(cb);

                       // UINT64 INPUT VALUES//

    // CircularBuffer *cb = InitCircularBuffer(N, UINT64);  // UINT64 VALUES //

    // uint64_t uint64_data = 123;
    // addToCircularBuffer(cb, &uint64_data,UINT64);
    // printf("value added to circular buffer: %u\n", *((uint64_t *)cb->buffer[cb->rear].buffer));
      //    printCircularBuffer(cb);

    // uint64_t uint64_data0 = 1234;
    // addToCircularBuffer(cb, &uint64_data0,UINT64);
      //    printCircularBuffer(cb);

    // uint64_t uint64_data1 = 12345;
    // addToCircularBuffer(cb, &uint64_data1,UINT64);
      //    printCircularBuffer(cb);

    // uint64_t uint64_data2 = 123456;
    // addToCircularBuffer(cb, &uint64_data2,UINT64);
      //    printCircularBuffer(cb);

    // uint64_t uint64_data3 = 1234567;
    // addToCircularBuffer(cb, &uint64_data3,UINT64);
      //    printCircularBuffer(cb);

    // uint64_t uint64_data4 = 12345678;
    // addToCircularBuffer(cb, &uint64_data4,UINT64);
      //    printCircularBuffer(cb);

    // uint64_t uint64_data5 = 123456789;
    // addToCircularBuffer(cb, &uint64_data5,UINT64);
      //    printCircularBuffer(cb);

    // uint64_t uint64_data6 = 1234567890;
    // addToCircularBuffer(cb, &uint64_data6,UINT64);
      //    printCircularBuffer(cb);

    // uint64_t uint64_data7 = 987654321;
    // addToCircularBuffer(cb, &uint64_data7,UINT64);
      //    printCircularBuffer(cb);


                        //FLOAT INPUT VALUES//

    // CircularBuffer *cb = InitCircularBuffer(N, FLOAT); // float values//

    // float float_data = 123.45f; //
    // addToCircularBuffer(cb, &float_data, FLOAT);
    // printCircularBuffer(cb);

    // float float_data0 = 1234.56f; //
    // addToCircularBuffer(cb, &float_data0, FLOAT);
    // printCircularBuffer(cb);

    // float float_data1 = 12345.67f; //
    // addToCircularBuffer(cb, &float_data1, FLOAT);
    // printCircularBuffer(cb);

    // float float_data2 = 123456.78f; //
    // addToCircularBuffer(cb, &float_data2, FLOAT);
    // printCircularBuffer(cb);

    // float float_data3 = 1234567.89f; //
    // addToCircularBuffer(cb, &float_data3, FLOAT);
    // printCircularBuffer(cb);

    // float float_data4 = 12345678.90f; //
    // addToCircularBuffer(cb, &float_data4, FLOAT);
    // printCircularBuffer(cb);

    // float float_data5 = 123456789.01f; //
    // addToCircularBuffer(cb, &float_data5, FLOAT);
    // printCircularBuffer(cb);

    // float float_data6 = 1234567890.12f; //
    // addToCircularBuffer(cb, &float_data6, FLOAT);
    // printCircularBuffer(cb);

    // float float_data7 = 987654321.23f; //
    // addToCircularBuffer(cb, &float_data7, FLOAT);
    // printCircularBuffer(cb);

    printf("Size of circular buffer: %d\n", cb->size);

    return 0;
}
