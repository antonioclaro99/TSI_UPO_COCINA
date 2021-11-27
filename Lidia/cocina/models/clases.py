# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Clases(models.Model):
    _name = 'cocina.clases'
    _description = 'cocina clases'

    nombreClase = fields.Char(string="Nombre Clase", size=60, required=True, help="Nombre de nuestra clase")
    fechaInicio = fields.Datetime("Fecha inicio", required=True, autodate=True)
    fechaFin = fields.Datetime("Fecha fin", required=True, autodate=True)
    aula_ids = fields.Many2one("cocina.aulas", string="Lista de aulas")
    cursos_ids= fields.Many2one('cocina.cursos', "Lista de cursos")
    #tema 6.1 pag 23 para hacer la funcion para la fecha onchange
    