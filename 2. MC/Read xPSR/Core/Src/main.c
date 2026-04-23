#define RCC_APB2ENR   (*(volatile unsigned int*)0x40021018) // RCC clock enable register
#define GPIOC_CRH     (*(volatile unsigned int*)0x40011004) // GPIOC configuration (pins 8–15)
#define GPIOC_ODR     (*(volatile unsigned int*)0x4001100C) // GPIOC output data register

// Simple delay for visible LED transition
void delay() {
    for (volatile int i = 0; i < 300000; i++);
}

int main(void) {

    volatile unsigned int psr_value; // Stores PSR (status register)
    int result;                      // Stores operation result

    // Enable clock for GPIOC
    RCC_APB2ENR |= (1 << 4);

    // Configure PC13 as output (LED pin)
    GPIOC_CRH &= ~(0xF << 20); // Clear bits
    GPIOC_CRH |=  (0x2 << 20); // Set as output (2 MHz)

    GPIOC_ODR |= (1 << 13); // Turn LED OFF (active LOW)

    while(1)
    {
        // ====================================================
        // 🔴 NEGATIVE FLAG (N)
        // Condition: result < 0
        // ====================================================

        // Clear all APSR flags (N, Z, C, V, Q)
        __asm volatile ("MSR APSR_nzcvq, %0" : : "r"(0) : "cc");

        int a = 5, b = -6; // Result will be negative

        // Perform addition and update flags
        __asm volatile (
            "ADDS %0, %1, %2"
            : "=r"(result)
            : "r"(a), "r"(b)
            : "cc"
        );

        // Read PSR value
        __asm volatile ("MRS %0, xPSR" : "=r"(psr_value));

        // Check bits 27–31 (Q, V, C, Z, N)
        for (int i = 27; i <= 31; i++) {
            if (psr_value & (1 << i)) {
                GPIOC_ODR &= ~(1 << 13); // LED ON
                GPIOC_ODR |= (1 << 13);  // LED OFF
            }
        }

        delay();

        // ====================================================
        // 🟢 ZERO (Z) and CARRY (C)
        // Condition: result = 0 and unsigned carry
        // ====================================================

        __asm volatile ("MSR APSR_nzcvq, %0" : : "r"(0) : "cc");

        a = 5; b = -5; // Result = 0

        __asm volatile (
            "ADDS %0, %1, %2"
            : "=r"(result)
            : "r"(a), "r"(b)
            : "cc"
        );

        __asm volatile ("MRS %0, xPSR" : "=r"(psr_value));

        for (int i = 27; i <= 31; i++) {
            if (psr_value & (1 << i)) {
                GPIOC_ODR &= ~(1 << 13);
                GPIOC_ODR |= (1 << 13);
            }
        }

        delay();

        // ====================================================
        // 🔵 OVERFLOW FLAG (V)
        // Condition: signed overflow occurs
        // Note: This operation also sets N flag because result becomes negative
        // ====================================================

        __asm volatile ("MSR APSR_nzcvq, %0" : : "r"(0) : "cc");

        a = 2147483647; b = 1; // Causes overflow

        __asm volatile (
            "ADDS %0, %1, %2"
            : "=r"(result)
            : "r"(a), "r"(b)
            : "cc"
        );

        __asm volatile ("MRS %0, xPSR" : "=r"(psr_value));

        for (int i = 27; i <= 31; i++) {
            if (psr_value & (1 << i)) {
                GPIOC_ODR &= ~(1 << 13);
                GPIOC_ODR |= (1 << 13);
            }
        }

        delay();

        // ====================================================
        // 🟡 Q FLAG (SATURATION)
        // Condition: value exceeds range and is clamped
        // ====================================================

        __asm volatile ("MSR APSR_nzcvq, %0" : : "r"(0) : "cc");

        int x = 1000; // Exceeds 8-bit range

        // Perform saturation
        __asm volatile (
            "SSAT %0, #8, %1"
            : "=r"(result)
            : "r"(x)
            : "cc"
        );

        __asm volatile ("MRS %0, xPSR" : "=r"(psr_value));

        for (int i = 27; i <= 31; i++) {
            if (psr_value & (1 << i)) {
            	GPIOC_ODR &= ~(1 << 13);
                GPIOC_ODR |= (1 << 13);
            }
        }

        delay();

        /*
           ====================================================
           🔵 LOGICAL OPERATIONS (ANDS / ORRS / EORS)
           These operations affect only N and Z flags
           ====================================================
        */

        // Clear all APSR flags first
        __asm volatile ("MSR APSR_nzcvq, %0" : : "r"(0) : "cc");

        a = 0x0F;   // 0000 1111
        b = 0xF0;   // 1111 0000

        // Choose ONE operation:

        __asm volatile (
            "ANDS %0, %1, %2"   // AND operation (result = 0)
            // "ORRS %0, %1, %2" // OR operation
            // "EORS %0, %1, %2" // XOR operation
            : "=r"(result)
            : "r"(a), "r"(b)
            : "cc"
        );

        // Read updated PSR value
        __asm volatile ("MRS %0, xPSR" : "=r"(psr_value));

        // Check APSR flags (bits 27–31)
        for (int i = 27; i <= 31; i++) {
            if (psr_value & (1 << i)) {
                GPIOC_ODR &= ~(1 << 13); // LED ON
                GPIOC_ODR |= (1 << 13);  // LED OFF
            }
        }

    }
}
