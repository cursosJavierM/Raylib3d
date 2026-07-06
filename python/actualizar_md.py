import re
from pathlib import Path

# CONFIGURACIÓN: Indica la carpeta donde están tus archivos Markdown
CARPETA_MARKDOWN = Path(".") 

# Patrón que busca la etiqueta oculta con el formato L1-L1 o L1-L10
PATRON = r"(<!-- embedme (.*?)#L(\d+)-L(\d+) -->\n```cpp\n)(.*?)(```)"

def actualizar_archivo_md(ruta_md):
    contenido_md = ruta_md.read_text(encoding="utf-8")
    
    if "<!-- embedme" not in contenido_md:
        return False

    def reemplazar_bloque(match):
        inicio_bloque = match.group(1)
        ruta_cpp_relativa = match.group(2)
        linea_inicio = int(match.group(3))
        linea_fin = int(match.group(4))
        cierre_bloque = match.group(6)
        
        archivo_cpp = Path(ruta_cpp_relativa)
        if not archivo_cpp.exists():
            print(f"⚠️  Advertencia: No se encontró el archivo C++ '{ruta_cpp_relativa}'")
            return match.group(0)
            
        lineas_cpp = archivo_cpp.read_text(encoding="utf-8").splitlines()
        
        # --- NUEVA LÓGICA: Añadir prefijo con el número de línea real ---
        lineas_con_numero = []
        for i in range(linea_inicio, linea_fin + 1):
            texto_linea = lineas_cpp[i - 1] # -1 porque Python cuenta desde 0
            # Formatea la línea para que quede "15 | código"
            lineas_con_numero.append(f"{i} | {texto_linea}")
            
        codigo_extraido = "\n".join(lineas_con_numero) + "\n"
        return f"{inicio_bloque}{codigo_extraido}{cierre_bloque}"

    nuevo_contenido = re.sub(PATRON, reemplazar_bloque, contenido_md, flags=re.DOTALL)
    
    if nuevo_contenido != contenido_md:
        ruta_md.write_text(nuevo_contenido, encoding="utf-8")
        return True
    return False

if __name__ == "__main__":
    print("🔍 Escaneando archivos Markdown...")
    archivos_modificados = 0
    for ruta_archivo in CARPETA_MARKDOWN.rglob("*.md"):
        try:
            if actualizar_archivo_md(ruta_archivo):
                print(f"✅ ¡Actualizado!: {ruta_archivo}")
                archivos_modificados += 1
        except Exception as e:
            print(f"❌ Error al procesar {ruta_archivo.name}: {e}")
    print(f"\n✨ Proceso terminado. Se actualizaron {archivos_modificados} archivos.")
