# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Personas(models.Model):
     
     _name = 'cocina.personas'
     _description = 'cocina personas'

     nombre = fields.Char(string="nombre", required=True, help="nombre de la persona")
     apellidos = fields.Char(string="apellidos", required=True, help="apellidos de la persona")
     dni = fields.Char('DNI', size=9, required=True)
     email  = fields.Char('Email', required=True)
     telefono  = fields.Integer('Telefono', required=True)


     #users_ids = fields.Many2many("gym.users",string="Confirmed users")
     #instructores_id=fields.Many2one('gym.instructores',string="Instructor")