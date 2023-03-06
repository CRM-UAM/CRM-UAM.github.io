---
layout: default
title: Lista de imágenes
permalink: /imagenes/
AVISO: Éste es el repositorio GitHub, la web está en http://crm.ii.uam.es/
---


Todas las imágenes de nuestro repositorio:
--


{% assign filenames = "" | split: ',' %}

{% for filed in site.static_files %}{% assign lcpath = filed.path | downcase %}
{% if lcpath contains '.jpg' %}{% assign filenames = filenames | push: filed.path %}{% endif %}
{% if lcpath contains '.jpeg' %}{% assign filenames = filenames | push: filed.path %}{% endif %}
{% if lcpath contains '.png' %}{% assign filenames = filenames | push: filed.path %}{% endif %}
{% endfor %}

<div style="width: 100%; display: flex; flex-wrap: wrap;">
{%- for name in filenames -%}
<div style="max-width: 144px; max-height: 108px; overflow:hidden;"><a href="{{ site.baseurl }}{{ name }}"><img src="{{ site.baseurl }}{{ name }}" alt="{{ name }}"/></a></div>
{%- endfor -%}
</div>
<br />

Todos los videos de nuestro repositorio:
--

{% for filed in site.static_files %}
    {% assign lcpath = filed.path | downcase %}
    {% if lcpath contains '.mp4' %}
<video width="320" height="240" controls><source src="{{ site.baseurl }}{{ filed.path }}" type="video/mp4"></video>
    {% endif %}
{% endfor %}
<br />

Más vídeos en otros formatos (click para descargar):
--

{% for filed in site.static_files %}
    {% assign lcpath = filed.path | downcase %}
    {% if lcpath contains '.mpg' %}
[{{ filed.path }}]({{ site.baseurl }}{{ filed.path }})
    {% endif %}
    {% if lcpath contains '.mpeg' %}
[{{ filed.path }}]({{ site.baseurl }}{{ filed.path }})
    {% endif %}
    {% if lcpath contains '.avi' %}
[{{ filed.path }}]({{ site.baseurl }}{{ filed.path }})
    {% endif %}
{% endfor %}

PS: ¡A cacharrear! :)
