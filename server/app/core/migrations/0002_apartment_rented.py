# Generated by Django 2.1.15 on 2021-07-07 20:02

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('core', '0001_initial'),
    ]

    operations = [
        migrations.AddField(
            model_name='apartment',
            name='rented',
            field=models.BooleanField(default=False),
        ),
    ]
