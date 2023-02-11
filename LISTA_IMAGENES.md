---
layout: default
permalink: /lista_imagenes/
AVISO: Éste es el repositorio GitHub, la web está en http://crm.ii.uam.es/
---


Todas las imágenes de nuestro repositorio:
--

{% for image in site.static_files %}
    {% if image.path|downcase contains '.jpg' %}
<img src="{{ site.baseurl }}{{ image.path }}" />
    {% endif %}
    {% if image.path|downcase contains '.jpeg' %}
<img src="{{ site.baseurl }}{{ image.path }}" />
    {% endif %}
    {% if image.path|downcase contains '.gif' %}
<img src="{{ site.baseurl }}{{ image.path }}" />
    {% endif %}
    {% if image.path|downcase contains '.png' %}
<img src="{{ site.baseurl }}{{ image.path }}" />
    {% endif %}
{% endfor %}

Todos los videos de nuestro repositorio:
--

{% for video in site.static_files %}
    {% if video.path|downcase contains '.mp4' %}
<video width="320" height="240" controls><source src="{{ site.baseurl }}{{ video.path }}" type="video/mp4"></video>
    {% endif %}
    {% if video.path|downcase contains '.mpg' %}
<video width="320" height="240" controls><source src="{{ site.baseurl }}{{ video.path }}" type="video/mpg"></video>
    {% endif %}
    {% if video.path|downcase contains '.mpeg' %}
<video width="320" height="240" controls><source src="{{ site.baseurl }}{{ video.path }}" type="video/mpeg"></video>
    {% endif %}
    {% if video.path|downcase contains '.avi' %}
<video width="320" height="240" controls><source src="{{ site.baseurl }}{{ video.path }}" type="video/avi"></video>
    {% endif %}
{% endfor %}

Todos los audios de nuestro repositorio:
--

{% for audio in site.static_files %}
    {% if audio.path|downcase contains '.mp3' %}
<audio controls><source src="{{ site.baseurl }}{{ audio.path }}" type="audio/mp3"></audio>
    {% endif %}
    {% if audio.path|downcase contains '.ogg' %}
<audio controls><source src="{{ site.baseurl }}{{ audio.path }}" type="audio/ogg"></audio>
    {% endif %}
    {% if audio.path|downcase contains '.wav' %}
<audio controls><source src="{{ site.baseurl }}{{ audio.path }}" type="audio/wav"></audio>
    {% endif %}
    {% if audio.path|downcase contains '.flac' %}
<audio controls><source src="{{ site.baseurl }}{{ audio.path }}" type="audio/flac"></audio>
    {% endif %}
{% endfor %}
