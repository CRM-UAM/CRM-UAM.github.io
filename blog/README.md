---
layout: page
title: Entradas del blog
permalink: /blog/
AVISO: Éste es el repositorio GitHub, la web está en http://crm.ii.uam.es/
---

<div class="home">

  <ul class="post-list">
    {% for post in site.posts %}
      <li>
        <span class="post-meta">{{ post.date | date: "%b %-d, %Y" }}</span>

        <h2>
          <a class="post-link" href="{{ post.url | prepend: site.baseurl }}">{{ post.title }}</a>
        </h2>
        {{ post.content }}
      <hr/>
      </li>
    {% endfor %}
  </ul>

  <p align="right" class="rss-subscribe">Añádenos a tu <a href="{{ "./feed.xml" | prepend: site.baseurl }}">lector RSS</a></p>

</div>
