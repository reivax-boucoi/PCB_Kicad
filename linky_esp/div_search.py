from itertools import product

# E12 resistor values
E12 = [1.0, 1.2, 1.5, 1.8, 2.2, 2.7,
       3.3, 3.9, 4.7, 5.6, 6.8, 8.2]

# Electrical parameters
Vb_min = float(input("Vbatt_min (V): "))
Vb_max = float(input("Vbatt_max (V): "))
Vth = float(input("Vth_onoff (V): "))
Ionoff = float(input("Ionoff (uA): ")) * 1e-6
Vadc_fs = 1.0
#float(input("Vadc_fs (V): "))

# Maximum acceptable early switching (volts)
tol = 0.015

# Generate E12 values, 1k to 1M
R = [x * 10**d for d in range(3, 7) for x in E12]

# R1 restricted to 22k - 100k
R1_values = [r for r in R if 10e3 <= r <= 330e3]

results = []

for R1, R2, R3 in product(R1_values, R, R):

    S = R2 + R3

    # Battery voltage at which ON/OFF reaches threshold
    Vtrip = Vth + R1 * (Vth / S - Ionoff)

    # Must switch on at Vb_min, but not too early
    if not (Vb_min - tol <= Vtrip <= Vb_min):
        continue

    # Maximum ADC voltage
    Vadc = R3 * (Vb_max + Ionoff * R1) / (R1 + S)

    if Vadc > Vadc_fs or Vadc < 0.5*Vadc_fs:
        continue

    results.append((Vadc, Vtrip, R1, R2, R3))

# Highest ADC utilization first
results.sort(key=lambda x: (-x[0], -x[1]))

print("\nBest E12 combinations:")
print(" R1(k)  R2(k)  R3(k)  Vtrip(V)  Vadc_max(V)")

for adc, trip, r1, r2, r3 in results[:10]:
    print(f"{r1/1e3:6.1f} {r2/1e3:6.1f} "
          f"{r3/1e3:6.1f} {trip:9.4f} {adc:12.4f}")
