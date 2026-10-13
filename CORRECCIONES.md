# Correcciones aplicadas — Práctica 06 (SIS210)

## Errores del código original
1. **Actividad 1 (Python):** `push`, `pop`, `enqueue` y `dequeue` eran `pass` (con `# COMPLETAR`).
   Con esa versión las pruebas con `assert` fallaban. Ahora están implementados en O(1);
   en `dequeue` se reinicia el puntero `_cola` cuando la cola queda vacía.
2. **Actividad 3 (Python):** en `evaluar_postfix` la clave de la suma era `','` en vez de `'+'`,
   por lo que cualquier expresión con suma fallaba.
3. **Actividad 5 (C++):** la función `bfs` estaba definida pero nunca se probaba en `main`.
   Se agregó una prueba con el grafo de Puno (orden esperado: 0 1 2 5 6 7 3 4 8 9),
   más casos extra de balanceo. Se quitó `<unordered_set>` (no se usaba) y se añadió `return 0;`.

## Mejoras de robustez (no cambian los resultados de los casos de la guía)
- `infix_a_postfix` ahora lanza `ValueError` si hay paréntesis sin pareja o un token no reconocido
  (por ejemplo `'2+3'` sin espacios), en lugar de fallar o devolver un resultado vacío.
- `evaluar_postfix` lanza `ValueError` claro si faltan operandos (antes: `IndexError` de `pop`).
- Se reemplazaron varios `print` de verificación por `assert` y se agregaron pruebas para
  cada función (requisito de la sección IV de la guía).

## Cómo ejecutar
- Python: abrir `Practica_S06_PilasColasDeque.ipynb` y ejecutar las celdas en orden.
- C++: `g++ -std=c++17 -O2 -Wall -o s06 Practica_S06_PilasColasDeque.cpp && ./s06`
