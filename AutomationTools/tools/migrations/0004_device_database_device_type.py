# -*- coding: utf-8 -*-
# Generated by Django 1.10.4 on 2017-02-24 18:33
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('tools', '0003_auto_20170120_2140'),
    ]

    operations = [
        migrations.AddField(
            model_name='device_database',
            name='device_type',
            field=models.CharField(default='Access', max_length=250),
        ),
    ]