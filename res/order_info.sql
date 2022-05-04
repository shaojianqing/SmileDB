-- smiledb.order_info definition

CREATE TABLE `order_info` (
  `order_id` varchar(36) NOT NULL,
  `product_id` varchar(36) NOT NULL,
  `product_name` varchar(100) NOT NULL,
  `unit_price` double NOT NULL,
  `currency` varchar(8) NOT NULL,
  `quantity` int(4) NOT NULL,
  `service_fee` double NOT NULL,
  `consumer_id` varchar(36) NOT NULL,
  `consumer_name` varchar(32) NOT NULL,
  `merchant_id` varchar(36) NOT NULL,
  `merchant_name` varchar(32) NOT NULL,
  `order_description` varchar(100) DEFAULT NULL,
  `is_valid` tinyint(1) NOT NULL,
  `gmt_create` datetime NOT NULL,
  `gmt_modified` datetime NOT NULL,
  PRIMARY KEY (`order_id`)
) ENGINE=InnoDB DEFAULT CHARSET=ascii;

-- order_id : 98b05da5008d4a1fa248c49efac93471
-- order_id : a69fdb97726e4a50a341ee41d51fbac9
-- order_id : 57198e76fe654d1cb81feb8711dcb99d
-- order_id : 881b8877df1641369dbf1f9ca09cf719
-- order_id : 8eb94a7dd3c9482b9be741d45fc56db5