---
layout: default
title: Lista de documentos
permalink: /documentos/
AVISO: Éste es el repositorio GitHub, la web está en http://crm.ii.uam.es/
---


Todos los ficheros de nuestro repositorio:
--

{% for filed in site.static_files %}
[{{ filed.path }}]({{ site.baseurl }}{{ filed.path }})
{% endfor %}
