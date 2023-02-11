---
layout: default
permalink: /lista_imagenes/
AVISO: Éste es el repositorio GitHub, la web está en http://crm.ii.uam.es/
---


Todas las imágenes de nuestro repositorio:
--

{% for image in site.static_files %}
    {% if {image.path | downcase} contains '.jpg' %}
        <img src="{{ site.baseurl }}{{ image.path }}" />
    {% endif %}
    {% if {image.path | downcase} contains '.jpeg' %}
        <img src="{{ site.baseurl }}{{ image.path }}" />
    {% endif %}
    {% if {image.path | downcase} contains '.gif' %}
        <img src="{{ site.baseurl }}{{ image.path }}" />
    {% endif %}
    {% if {image.path | downcase} contains '.png' %}
        <img src="{{ site.baseurl }}{{ image.path }}" />
    {% endif %}
{% endfor %}
