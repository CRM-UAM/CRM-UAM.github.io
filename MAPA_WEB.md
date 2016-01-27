---
layout: default
permalink: /mapa_web/
AVISO: Éste es el repositorio GitHub, la web está en http://crm.ii.uam.es/
---


Lista de páginas
--

<ul>
{% for page in site.pages %}
  <li>
{% if page.title %}
      <b><a href="{{ site.url }}{{ site.baseurl }}{{ page.url }}">{{ page.title }}</a></b>
{% else %}
      <i><a href="{{ site.url }}{{ site.baseurl }}{{ page.url }}">{{ site.url }}{{ site.baseurl }}{{ page.url }}</a></i>
{% endif %}
  </li>
{% endfor %}
</ul>


Lista de entradas del blog
--

<ul>
{% for post in site.posts %}
  <li>
      <a href="{{ post.url | prepend: site.baseurl }}">{{ post.title }}</a>
  </li>
{% endfor %}
</ul>

